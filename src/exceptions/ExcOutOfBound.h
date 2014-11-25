#pragma once
#include "Exceptions.h"

class ExcOutOfBound: public Exceptions {
    public:
      ExcOutOfBound();
      virtual ~ExcOutOfBound();
      
      private:
        virtual const int errNo() const throw();
};
