#ifndef LW_DATABASE_H
#define LW_DATABASE_H

#include "linked_list.h"

#include <filesystem>

namespace db {

    enum car_status : int {
        free             = 1,
        has_order        = 2,
        fulfilling_order = 3,
        in_repair        = 4,
        MAX,
    };

    std::string format_status(const car_status& status);

    struct car_row {
        std::string car_type;
        std::string car_model;
        std::string car_plate;
        std::string car_capacity;
        time_t next_inspection_date;
        car_status car_status;
        time_t order_date;
    };

    std::string format_row(const car_row& car);

    struct database {
        llist::linked_list<car_row> _list{};
    };

    int row_count(db::database *db);

    // copies this row into the database
    void add_row(db::database *db, const db::car_row &new_row);

    void print(db::database *db);

    void save_to_file(db::database *db, const std::filesystem::path& output_path);

    void read_from_file(database *db, const std::filesystem::path& input_path);

    void erase(database *db, int index);

    void clear(database *db);

    template<class T>
    void sort(database *db, T comp) {
        auto *new_list = new llist::linked_list<car_row>;
        while(!db->_list.empty()) {
            auto current = db->_list.begin();
            auto smallest = current;
            while(current != nullptr) {
                if(comp(current->data, smallest->data)) {
                    smallest = current;
                }
            }
            new_list->push_back(smallest->data);
            db->_list.erase(smallest);
        }
        db->_list = *new_list; // copy
        delete new_list;
    }

    template<class T>
    void filter(database *db, T filt) {
        auto *new_list = new llist::linked_list<car_row>;
        if(db->_list.empty())
            return;

        auto current = db->_list.begin();
        auto smallest = current;
        while(current != nullptr) {
            if(filt(current->data)) {
                new_list->push_back(smallest->data);
            }
        }

        db->_list.clear();
        db->_list = *new_list; // copy
        delete new_list;
    }

} // db

#endif //LW_DATABASE_H
