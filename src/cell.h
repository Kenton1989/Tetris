#ifndef CELL_H
#define CELL_H

#include <utility>

struct Cell {
public:
    using ApperanceT = int;

    Cell() {};
    explicit Cell(ApperanceT a): emp_(false), app_(a) {}

    bool empty() const { return emp_; };
    void clear() { emp_ = true; }

    const ApperanceT& apperance() const { return app_; }
    void setApperance(const ApperanceT& a) { app_ = a; emp_ = false; }
    void setApperance(ApperanceT&& a) { app_ = std::move(a); emp_ = false; }

private:
    bool emp_ = true;
    ApperanceT app_;
};


#endif // CELL_H
