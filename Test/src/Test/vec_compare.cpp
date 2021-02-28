/* 
 * Created by Matthias "Nelaty" Gensheimer on 24.02.21.
 * Copyright (c) 2021 Matthias Gensheimer. All rights reserved.
 */

#include <Test/vec_compare.h>
#include <ThirdParty/catch.hpp>

#include <sstream>

namespace test
{
    bool compareApprox(const glm::vec2& a, const glm::vec2& b)
    {
        return a.x == Approx(b.x)
            && a.y == Approx(b.y);
    }

    bool compareApprox(const glm::vec3& a, const glm::vec3& b)
    {
        return a.x == Approx(b.x)
            && a.y == Approx(b.y)
            && a.z == Approx(b.z);
    }

    bool compareApprox(const glm::vec4& a, const glm::vec4& b)
    {
        return a.x == Approx(b.x)
            && a.y == Approx(b.y)
            && a.z == Approx(b.z)
            && a.w == Approx(b.w);
    }

    std::string vecToString(const glm::vec2& val)
    {
        std::ostringstream oss;
        oss << val.x << " " << val.y;
        return oss.str();
    }

    std::string vecToString(const glm::vec3& val)
    {
        std::ostringstream oss;
        oss << val.x << " " << val.y << " " << val.z;
        return oss.str();
    }

    std::string vecToString(const glm::vec4& val)
    {
        std::ostringstream oss;
        oss << val.x << " " << val.y << val.z << " " << val.w;
        return oss.str();
    }
}