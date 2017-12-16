#pragma once

#include "view/page.h"

namespace view {

class IPageStack {
   public:
    virtual ~IPageStack() {}
    virtual void push(Page *page) = 0;
    virtual void pop() = 0;
    virtual Page *currentPage() = 0;
};

}  // namespace view