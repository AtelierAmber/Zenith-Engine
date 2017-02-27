#pragma once

namespace Zenith {
    typedef unsigned char GLubyte;
    struct Position {
        Position() : x(0.0f), y(0.0f), z(0.0f) {}
        Position(const Position& pos) : x(pos.x), y(pos.y), z(pos.z) {}
        Position(const float& X, const float& Y, const float& Z) : x(X), y(Y), z(Z) { }
        float x;
        float y;
        float z;
    };

    struct ColorRGBA8 {
        //Constructors
        ColorRGBA8() : r(0), g(0), b(0), a(255) { }
        ColorRGBA8(const ColorRGBA8& col) : r(col.r), g(col.g), b(col.b), a(col.a) {}
        ColorRGBA8(const GLubyte& R, const GLubyte& G, const GLubyte& B, const GLubyte& A) : r(R), g(G), b(B), a(A) { }

        GLubyte r;
        GLubyte g;
        GLubyte b;
        GLubyte a;
    };

    struct UV {
        UV() : u(0.0f), v(0.0f) {}
        UV(const UV& uv) : u(uv.u), v(uv.v) {}
        UV(const float& U, const float& V) : u(U), v(V) { }
        float u;
        float v;
    };

    struct Normal {
        Normal() : nx(0.0f), ny(0.0f), nz(0.0f) {}
        Normal(const Normal& nor) : nx(nor.nx), ny(nor.ny), nz(nor.nz) {}
        Normal(const float& NX, const float& NY, const float& NZ) : nx(NX), ny(NY), nz(NZ) { }
        float nx;
        float ny;
        float nz;
    };

    //The vertex definition
    struct Vertex {
        //Base constructors
        Vertex() : position(), color(), uv(), normal() { }
        Vertex(const Position& pos, const ColorRGBA8& Color, const UV& Uv, const Normal& nor) : 
            position(pos), color(Color), uv(Uv), normal(nor) { }
        Vertex(const float& x, float& y, float& z, const ColorRGBA8& Color, const UV& Uv, const Normal& nor) : 
            position(x, y, z), color(Color), uv(Uv) { }
        Vertex(const float& x, const float& y, const float& z, const GLubyte& r, 
            const GLubyte& g, const GLubyte& b, const GLubyte& a, const UV& Uv, const Normal& nor) : 
            position(x, y, z), color(r, g, b, a), uv(Uv) { }
        Vertex(const float& x, const float& y, const float& z, const GLubyte& r, 
            const GLubyte& g, const GLubyte& b, const GLubyte& a, const float& u, 
            const float& v, const Normal& nor) :
            position(x, y, z), color(r, g, b, a), uv(u, v) { }
        Vertex(const float& x, const float& y, const float& z, const GLubyte& r,
            const GLubyte& g, const GLubyte& b, const GLubyte& a, const float& u, 
            const float& v, const float& nx, const float& ny, const float& nz) :
            position(x, y, z), color(r, g, b, a), uv(u, v), normal(nx, ny, nz){ }

        Position position;

        /* 4 bytes for r g b a color. */
        ColorRGBA8 color;

        /* UV texture coordinates. */
        UV uv;

        Normal normal;

        void setPosition(float x, float y, float z) {
            position.x = x;
            position.y = y;
            position.z = z;
        }

        void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
            color.r = r;
            color.g = g;
            color.b = b;
            color.a = a;
        }

        void setUV(float u, float v) {
            uv.u = u;
            uv.v = v;
        }

        void setNormal(float nx, float ny, float nz) {
            normal.nx = nx;
            normal.ny = ny;
            normal.nz = nz;
        }
    };

}