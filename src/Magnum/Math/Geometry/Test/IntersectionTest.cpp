/*
    This file is part of Magnum.

    Copyright © 2010, 2011, 2012, 2013, 2014, 2015
              Vladimír Vondruš <mosra@centrum.cz>

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
*/

#include <Corrade/TestSuite/Tester.h>

#include "Magnum/Math/Geometry/Intersection.h"

namespace Magnum { namespace Math { namespace Geometry { namespace Test {

struct IntersectionTest: Corrade::TestSuite::Tester {
    explicit IntersectionTest();

    void planeLine();
    void lineLine();
};

typedef Math::Vector2<Float> Vector2;
typedef Math::Vector3<Float> Vector3;
typedef Math::Constants<Float> Constants;

IntersectionTest::IntersectionTest() {
    addTests({&IntersectionTest::planeLine,
              &IntersectionTest::lineLine});
}

void IntersectionTest::planeLine() {
    const Vector3 planePosition(-1.0f, 1.0f, 0.5f);
    const Vector3 planeNormal(0.0f, 0.0f, 1.0f);

    /* Inside line segment */
    CORRADE_COMPARE(Intersection::planeLine(planePosition, planeNormal,
        {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f, 2.0f}), 0.75f);

    /* Outside line segment */
    CORRADE_COMPARE(Intersection::planeLine(planePosition, planeNormal,
        {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}), -0.5f);

    /* Line lies on the plane */
    CORRADE_COMPARE(Intersection::planeLine(planePosition, planeNormal,
        {1.0f, 0.5f, 0.5f}, {-1.0f, 0.5f, 0.0f}), Constants::nan());

    /* Line is parallel to the plane */
    CORRADE_COMPARE(Intersection::planeLine(planePosition, planeNormal,
        {1.0f, 0.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}), -Constants::inf());
}

void IntersectionTest::lineLine() {
    const Vector2 p(-1.0f, -1.0f);
    const Vector2 r(1.0, 2.0f);

    /* Inside both line segments */
    CORRADE_COMPARE(Intersection::lineSegmentLineSegment(p, r,
        {0.0f, 0.0f}, {-1.0f, 0.0f}), std::make_pair(0.5f, 0.5f));
    CORRADE_COMPARE(Intersection::lineSegmentLine(p, r,
        {0.0f, 0.0f}, {-1.0f, 0.0f}), 0.5);

    /* Outside both line segments */
    CORRADE_COMPARE(Intersection::lineSegmentLineSegment(p, r,
        {0.0f, -2.0f}, {-1.0f, 0.0f}), std::make_pair(-0.5f, 1.5f));
    CORRADE_COMPARE(Intersection::lineSegmentLine(p, r,
        {0.0f, -2.0f}, {-1.0f, 0.0f}), -0.5f);

    /* Collinear lines */
    const auto tu = Intersection::lineSegmentLineSegment(p, r,
        {0.0f, 1.0f}, {-1.0f, -2.0f});
    CORRADE_COMPARE(tu.first, -Constants::nan());
    CORRADE_COMPARE(tu.second, -Constants::nan());
    CORRADE_COMPARE(Intersection::lineSegmentLine(p, r,
        {0.0f, 1.0f}, {-1.0f, -2.0f}), -Constants::nan());

    /* Parallel lines */
    CORRADE_COMPARE(Intersection::lineSegmentLineSegment(p, r,
        {0.0f, 0.0f}, {1.0f, 2.0f}), std::make_pair(Constants::inf(), Constants::inf()));
    CORRADE_COMPARE(Intersection::lineSegmentLine(p, r,
        {0.0f, 0.0f}, {1.0f, 2.0f}), Constants::inf());
}

}}}}

CORRADE_TEST_MAIN(Magnum::Math::Geometry::Test::IntersectionTest)
