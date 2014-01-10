/*
    This file is part of Magnum.

    Copyright © 2010, 2011, 2012, 2013 Vladimír Vondruš <mosra@centrum.cz>

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

#include "AbstractShape.h"

#include <Utility/Debug.h>

#include "Shapes/ShapeGroup.h"
#include "Shapes/Implementation/CollisionDispatch.h"

namespace Magnum { namespace Shapes {

template<UnsignedInt dimensions> AbstractShape<dimensions>::AbstractShape(SceneGraph::AbstractObject<dimensions, Float>& object, ShapeGroup<dimensions>* group): SceneGraph::AbstractGroupedFeature<dimensions, AbstractShape<dimensions>, Float>(object, group) {
    SceneGraph::AbstractFeature<dimensions, Float>::setCachedTransformations(SceneGraph::CachedTransformation::Absolute);
}

template<UnsignedInt dimensions> ShapeGroup<dimensions>* AbstractShape<dimensions>::group() {
    return static_cast<ShapeGroup<dimensions>*>(SceneGraph::AbstractGroupedFeature<dimensions, AbstractShape<dimensions>, Float>::group());
}

template<UnsignedInt dimensions> const ShapeGroup<dimensions>* AbstractShape<dimensions>::group() const {
    return static_cast<const ShapeGroup<dimensions>*>(SceneGraph::AbstractGroupedFeature<dimensions, AbstractShape<dimensions>, Float>::group());
}

template<UnsignedInt dimensions> auto AbstractShape<dimensions>::type() const -> Type {
    return abstractTransformedShape().type();
}

template<UnsignedInt dimensions> bool AbstractShape<dimensions>::collides(const AbstractShape<dimensions>& other) const {
    return Implementation::collides(abstractTransformedShape(), other.abstractTransformedShape());
}

template<UnsignedInt dimensions> void AbstractShape<dimensions>::markDirty() {
    if(group()) group()->setDirty();
}

#ifndef DOXYGEN_GENERATING_OUTPUT
template class MAGNUM_SHAPES_EXPORT AbstractShape<2>;
template class MAGNUM_SHAPES_EXPORT AbstractShape<3>;
#endif

}}