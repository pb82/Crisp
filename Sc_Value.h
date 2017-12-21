//
// Created by peter on 12.12.17.
//

#ifndef CRISP_SC_VALUE_H
#define CRISP_SC_VALUE_H

#include <ostream>

namespace Crisp {

    enum Sc_Type {
        CELL,
        NUMBER,
        PROC,
        REF,
        SEXPR
    };

    class Sc_Value {
    public:
        Sc_Value(Sc_Type type) : type(type), GC_mark(false) {

        }

        virtual ~Sc_Value() = default;
        virtual void toString(std::ostream &out) const = 0;

        Sc_Type getType() const;

        // Used by the garbage collector
        bool marked() const;
        void mark(bool val);

        int getLine() const;
        int getPosition() const;
        void setLine(int line);
        void setPosition(int position);
    private:
        Sc_Type type;

        // Mark/Sweep GC flag
        bool GC_mark;

        // Source references
        int line;
        int position;
    };

}

#endif //CRISP_SC_VALUE_H
