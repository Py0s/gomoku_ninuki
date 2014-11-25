#include "ExcOutOfBound.h"

ExcOutOfBound::ExcOutOfBound(): Exceptions("Out of boundaries") {
}

ExcOutOfBound::~ExcOutOfBound() {
}

// Members
const int ExcOutOfBound::errNo() const throw () {
    return 2;
}