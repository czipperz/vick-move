#include <boost/optional.hpp>

#include "../../../src/change.hh"

struct move_change : public change {
    move_change(std::function<std::shared_ptr<change>(const contents&)>,
                unsigned long oldy, unsigned long oldx,
                unsigned long y,    unsigned long x);
    virtual ~move_change() {}
    virtual void undo(contents&);
    virtual void redo(contents&);
    virtual std::shared_ptr<change> regenerate(const contents&) const;
};
