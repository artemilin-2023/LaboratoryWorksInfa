//
// Created by y7o4ka on 27.10.2024.
//

#ifndef LW_INDENTED_HELPERS_H
#define LW_INDENTED_HELPERS_H

#include <iostream>

namespace m {
    std::ostream &start_indent(std::ostream &o);

    std::ostream &end_indent(std::ostream &o);

    std::ostream &print_indent(std::ostream &o);
}

#endif //LW_INDENTED_HELPERS_H
