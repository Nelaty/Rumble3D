/* 
 * Created by Matthias "Nelaty" Gensheimer on 24.02.21.
 * Copyright (c) 2021 Matthias Gensheimer. All rights reserved.
 */

#pragma once

#include <glm/glm.hpp>
#include <string>
#include <iostream>

namespace test
{
    bool compareApprox(const glm::vec2 &a, const glm::vec2 &b);
    bool compareApprox(const glm::vec3 &a, const glm::vec3 &b);
    bool compareApprox(const glm::vec4 &a, const glm::vec4 &b);

    bool compareRangeApprox(const glm::vec3 &val,
                            const glm::vec3 &start,
                            const glm::vec3 &end);

    std::string vecToString(const glm::vec2& val);
    std::string vecToString(const glm::vec3& val);
    std::string vecToString(const glm::vec4& val);
}