#ifndef Magnum_RectangleTexture_h
#define Magnum_RectangleTexture_h
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

#ifndef MAGNUM_TARGET_GLES
/** @file
 * @brief Class @ref Magnum::RectangleTexture
 */
#endif

#include "Magnum/AbstractTexture.h"
#include "Magnum/Array.h"
#include "Magnum/Math/Vector2.h"

#ifndef MAGNUM_TARGET_GLES
namespace Magnum {

/**
@brief Rectangle texture

See also @ref AbstractTexture documentation for more information.

## Usage

Common usage is to fully configure all texture parameters and then set the
data from e.g. @ref Image2D. Example configuration:
@code
Image2D image(ColorFormat::RGBA, ColorType::UnsignedByte, {526, 137}, data);

RectangleTexture texture;
texture.setMagnificationFilter(Sampler::Filter::Linear)
    .setMinificationFilter(Sampler::Filter::Linear)
    .setWrapping(Sampler::Wrapping::ClampToEdge)
    .setMaxAnisotropy(Sampler::maxMaxAnisotropy())
    .setStorage(TextureFormat::RGBA8, {526, 137})
    .setSubImage({}, image);
@endcode

In shader, the texture is used via sampler2DRect`, `sampler2DRectShadow`,
`isampler2DRect` or `usampler2DRect`. See @ref AbstractShaderProgram
documentation for more information about usage in shaders.

@see @ref Texture, @ref TextureArray, @ref CubeMapTexture,
    @ref CubeMapTextureArray, @ref BufferTexture, @ref MultisampleTexture
@requires_gl31 Extension @extension{ARB,texture_rectangle}
@requires_gl Rectangle textures are not available in OpenGL ES.
 */
class MAGNUM_EXPORT RectangleTexture: public AbstractTexture {
    public:
        /**
         * @brief Max supported rectangle texture size
         *
         * The result is cached, repeated queries don't result in repeated
         * OpenGL calls. If @extension{ARB,texture_rectangle} (part of
         * OpenGL 3.1) is not available, returns zero vector.
         * @see @fn_gl{Get} with @def_gl{MAX_RECTANGLE_TEXTURE_SIZE}
         */
        static Vector2i maxSize();

        /**
         * @brief Constructor
         *
         * Creates new OpenGL texture object. If @extension{ARB,direct_state_access}
         * (part of OpenGL 4.5) is not supported, the texture is created on
         * first use.
         * @see @fn_gl{CreateTextures}  with @def_gl{TEXTURE_RECTANGLE},
         *      eventually @fn_gl{GenTextures}
         */
        explicit RectangleTexture(): AbstractTexture(GL_TEXTURE_RECTANGLE) {}

        /**
         * @copybrief Texture::setMinificationFilter()
         * @return Reference to self (for method chaining)
         *
         * See @ref Texture::setMinificationFilter() for more information.
         * Initial value is @ref Sampler::Filter::Linear.
         */
        RectangleTexture& setMinificationFilter(Sampler::Filter filter) {
            AbstractTexture::setMinificationFilter(filter, Sampler::Mipmap::Base);
            return *this;
        }

        /**
         * @copybrief Texture::setMagnificationFilter()
         * @return Reference to self (for method chaining)
         *
         * See @ref Texture::setMagnificationFilter() for more information.
         */
        RectangleTexture& setMagnificationFilter(Sampler::Filter filter) {
            AbstractTexture::setMagnificationFilter(filter);
            return *this;
        }

        /**
         * @copybrief Texture::setWrapping()
         * @return Reference to self (for method chaining)
         *
         * Sets wrapping type for coordinates out of @f$ [ 0, size - 1 ] @f$
         * range. See @ref Texture::setWrapping() for more information. Initial
         * value is @ref Sampler::Wrapping::ClampToEdge.
         * @attention Only @ref Sampler::Wrapping::ClampToEdge and
         *      @ref Sampler::Wrapping::ClampToBorder is supported on this
         *      texture type.
         */
        RectangleTexture& setWrapping(const Array2D<Sampler::Wrapping>& wrapping) {
            DataHelper<2>::setWrapping(*this, wrapping);
            return *this;
        }

        /**
         * @copybrief Texture::setBorderColor(const Color4&)
         * @return Reference to self (for method chaining)
         *
         * See @ref Texture::setBorderColor(const Color4&) for more
         * information.
         */
        RectangleTexture& setBorderColor(const Color4& color) {
            AbstractTexture::setBorderColor(color);
            return *this;
        }

        /**
         * @copybrief Texture::setBorderColor(const Vector4ui&)
         * @return Reference to self (for method chaining)
         *
         * See @ref Texture::setBorderColor(const Vector4ui&) for more
         * information.
         * @requires_gl30 Extension @extension{EXT,texture_integer}
         */
        RectangleTexture& setBorderColor(const Vector4ui& color) {
            AbstractTexture::setBorderColor(color);
            return *this;
        }

        /** @overload
         * @requires_gl30 Extension @extension{EXT,texture_integer}
         */
        RectangleTexture& setBorderColor(const Vector4i& color) {
            AbstractTexture::setBorderColor(color);
            return *this;
        }

        /**
         * @copybrief Texture::setMaxAnisotropy()
         * @return Reference to self (for method chaining)
         *
         * See @ref Texture::setMaxAnisotropy() for more information.
         */
        RectangleTexture& setMaxAnisotropy(Float anisotropy) {
            AbstractTexture::setMaxAnisotropy(anisotropy);
            return *this;
        }

        /**
         * @copybrief Texture::setSRGBDecode()
         * @return Reference to self (for method chaining)
         *
         * See @ref Texture::setSRGBDecode() for more information.
         * @requires_extension Extension @extension{EXT,texture_sRGB_decode}
         */
        RectangleTexture& setSRGBDecode(bool decode) {
            AbstractTexture::setSRGBDecode(decode);
            return *this;
        }

        /**
         * @copybrief Texture::setSwizzle()
         * @return Reference to self (for method chaining)
         *
         * See @ref Texture::setSwizzle() for more information.
         * @requires_gl33 Extension @extension{ARB,texture_swizzle}
         */
        template<char r, char g, char b, char a> RectangleTexture& setSwizzle() {
            AbstractTexture::setSwizzle<r, g, b, a>();
            return *this;
        }

        /**
         * @copybrief Texture::setCompareMode()
         * @return Reference to self (for method chaining)
         *
         * See @ref Texture::setCompareMode() for more information.
         */
        RectangleTexture& setCompareMode(Sampler::CompareMode mode) {
            AbstractTexture::setCompareMode(mode);
            return *this;
        }

        /**
         * @copybrief Texture::setCompareFunction()
         * @return Reference to self (for method chaining)
         *
         * See @ref Texture::setCompareFunction() for more information.
         */
        RectangleTexture& setCompareFunction(Sampler::CompareFunction function) {
            AbstractTexture::setCompareFunction(function);
            return *this;
        }

        /**
         * @copybrief Texture::setDepthStencilMode()
         * @return Reference to self (for method chaining)
         *
         * See @ref Texture::setDepthStencilMode() for more information.
         * @requires_gl43 Extension @extension{ARB,stencil_texturing}
         */
        RectangleTexture& setDepthStencilMode(Sampler::DepthStencilMode mode) {
            AbstractTexture::setDepthStencilMode(mode);
            return *this;
        }

        /**
         * @copybrief Texture::setStorage()
         * @return Reference to self (for method chaining)
         *
         * See @ref Texture::setStorage() for more information.
         * @see @ref maxSize()
         */
        RectangleTexture& setStorage(TextureFormat internalFormat, const Vector2i& size) {
            DataHelper<2>::setStorage(*this, 1, internalFormat, size);
            return *this;
        }

        /**
         * @brief Texture image size
         *
         * See @ref Texture::imageSize() for more information.
         */
        Vector2i imageSize() { return DataHelper<2>::imageSize(*this, 0); }

        /**
         * @brief Read texture to image
         *
         * See @ref Texture::image(Int, Image&) for more information.
         */
        void image(Image2D& image) {
            AbstractTexture::image<2>(0, image);
        }

        /** @overload
         *
         * Convenience alternative to the above, example usage:
         * @code
         * Image2D image = texture.image({ColorFormat::RGBA, ColorType::UnsignedByte});
         * @endcode
         */
        Image2D image(Image2D&& image);

        /**
         * @brief Read texture to buffer image
         *
         * See @ref Texture::image(Int, BufferImage&, BufferUsage) for more
         * information.
         */
        void image(BufferImage2D& image, BufferUsage usage) {
            AbstractTexture::image<2>(0, image, usage);
        }

        /** @overload
         *
         * Convenience alternative to the above, example usage:
         * @code
         * BufferImage2D image = texture.image({ColorFormat::RGBA, ColorType::UnsignedByte}, BufferUsage::StaticRead);
         * @endcode
         */
        BufferImage2D image(BufferImage2D&& image, BufferUsage usage);

        /**
         * @copybrief Texture::subImage(Int, const RangeTypeFor<dimensions, Int>&, Image&)
         *
         * See @ref Texture::subImage(Int, const RangeTypeFor<dimensions, Int>&, Image&)
         * for more information.
         * @requires_gl45 Extension @extension{ARB,get_texture_sub_image}
         */
        void subImage(const Range2Di& range, Image2D& image) {
            AbstractTexture::subImage<2>(0, range, image);
        }

        /** @overload
         *
         * Convenience alternative to the above, example usage:
         * @code
         * Image2D image = texture.subImage(range, {ColorFormat::RGBA, ColorType::UnsignedByte});
         * @endcode
         */
        Image2D subImage(const Range2Di& range, Image2D&& image);

        /**
         * @copybrief Texture::subImage(Int, const RangeTypeFor<dimensions, Int>&, BufferImage&, BufferUsage)
         *
         * See @ref Texture::subImage(Int, const RangeTypeFor<dimensions, Int>&, BufferImage&, BufferUsage)
         * for more information.
         * @requires_gl45 Extension @extension{ARB,get_texture_sub_image}
         */
        void subImage(const Range2Di& range, BufferImage2D& image, BufferUsage usage) {
            AbstractTexture::subImage<2>(0, range, image, usage);
        }

        /** @overload
         *
         * Convenience alternative to the above, example usage:
         * @code
         * BufferImage2D image = texture.subImage(range, {ColorFormat::RGBA, ColorType::UnsignedByte}, BufferUsage::StaticRead);
         * @endcode
         */
        BufferImage2D subImage(const Range2Di& range, BufferImage2D&& image, BufferUsage usage);

        /**
         * @copybrief Texture::setImage()
         * @return Reference to self (for method chaining)
         *
         * See @ref Texture::setImage() for more information.
         * @see @ref maxSize()
         * @deprecated_gl Prefer to use @ref Magnum::RectangleTexture::setStorage() "setStorage()"
         *      and @ref Magnum::RectangleTexture::setSubImage() "setSubImage()"
         *      instead.
         */
        RectangleTexture& setImage(TextureFormat internalFormat, const ImageReference2D& image) {
            DataHelper<2>::setImage(*this, 0, internalFormat, image);
            return *this;
        }

        /** @overload
         * @deprecated_gl Prefer to use @ref Magnum::RectangleTexture::setStorage() "setStorage()"
         *      and @ref Magnum::RectangleTexture::setSubImage() "setSubImage()"
         *      instead.
         */
        RectangleTexture& setImage(TextureFormat internalFormat, BufferImage2D& image) {
            DataHelper<2>::setImage(*this, 0, internalFormat, image);
            return *this;
        }

        /** @overload
         * @deprecated_gl Prefer to use @ref Magnum::RectangleTexture::setStorage() "setStorage()"
         *      and @ref Magnum::RectangleTexture::setSubImage() "setSubImage()"
         *      instead.
         */
        RectangleTexture& setImage(TextureFormat internalFormat, BufferImage2D&& image) {
            return setImage(internalFormat, image);
        }

        /**
         * @copybrief Texture::setSubImage()
         * @return Reference to self (for method chaining)
         *
         * See @ref Texture::setSubImage() for more information.
         */
        RectangleTexture& setSubImage(const Vector2i& offset, const ImageReference2D& image) {
            DataHelper<2>::setSubImage(*this, 0, offset, image);
            return *this;
        }

        /** @overload */
        RectangleTexture& setSubImage(const Vector2i& offset, BufferImage2D& image) {
            DataHelper<2>::setSubImage(*this, 0, offset, image);
            return *this;
        }

        /** @overload */
        RectangleTexture& setSubImage(const Vector2i& offset, BufferImage2D&& image) {
            return setSubImage(offset, image);
        }

        /**
         * @brief Invalidate texture
         *
         * See @ref Texture::invalidateImage() for more information.
         */
        void invalidateImage() { AbstractTexture::invalidateImage(0); }

        /**
         * @brief Invalidate subtexture
         * @param offset            Offset into the texture
         * @param size              Size of invalidated data
         *
         * See @ref Texture::invalidateSubImage() for more information.
         */
        void invalidateSubImage(const Vector2i& offset, const Vector2i& size) {
            DataHelper<2>::invalidateSubImage(*this, 0, offset, size);
        }

        /* Overloads to remove WTF-factor from method chaining order */
        #ifndef DOXYGEN_GENERATING_OUTPUT
        RectangleTexture& setLabel(const std::string& label) {
            AbstractTexture::setLabel(label);
            return *this;
        }
        template<std::size_t size> RectangleTexture& setLabel(const char(&label)[size]) {
            AbstractTexture::setLabel<size>(label);
            return *this;
        }
        #endif
};

}
#else
#error this header is available only on desktop OpenGL build
#endif

#endif
