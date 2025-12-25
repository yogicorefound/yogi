//
// Created by Brayhan De Aza on 11/27/25.
//

#pragma once

#include "semantic/arrays/Arrays.h"
#include "semantic/dictionaries/Dictionaries.h"
#include "semantic/variables/Variables.h"

namespace yogi::semantic {
    class Semantic : public virtual Variables, public virtual Arrays, public virtual Dictionaries {};
} // namespace yogi::semantic
