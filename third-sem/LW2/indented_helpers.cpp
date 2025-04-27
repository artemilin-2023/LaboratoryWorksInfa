//
// Created by y7o4ka on 27.10.2024.
//

#include "indented_helpers.h"
#include <iostream>


namespace m {
    static int indent_count = 0;

    std::ostream &start_indent(std::ostream &o) {
        for (int i = 0; i < indent_count; ++i) {
            o << "│";
        }
        indent_count++;
        return o << "╭ ";
    }

    std::ostream &end_indent(std::ostream &o) {
        indent_count--;
        for (int i = 0; i < indent_count; ++i) {
            o << "│";
        }
        return o << "╰ ";
    }

    std::ostream &print_indent(std::ostream &o) {
        for (int i = 0; i < indent_count; ++i) {
            o << "│";
        }
        return o << " ";
    }
}