#pragma once

namespace Zenith {
    typedef unsigned char GLubyte;
    struct Position {
        Position() : x(0.0f), y(0.0f), z(0.0f) {}
        Position(const Position& pos) : x(pos.x), y(pos.y), z(pos.z) {}
        Position(float X, float Y, float Z) : x(X), y(Y), z(Z) { }
        float x;
        float y;
        float z;
    };

    struct ColorRGBA8 {
        //Constructors
        ColorRGBA8() : r(0), g(0), b(0), a(255) { }
        ColorRGBA8(const ColorRGBA8& col) : r(col.r), g(col.g), b(col.b), a(col.a) {}
        ColorRGBA8(GLubyte R, GLubyte G, GLubyte B, GLubyte A) : r(R), g(G), b(B), a(A) { }

        GLubyte r;
        GLubyte g;
        GLubyte b;
        GLubyte a;
    };

    struct UV {
        UV(const UV& uv) : u(uv.u), v(uv.v) {}
        UV(float U, float V) : u(U), v(V) { }
        float u;
        float v;
    };

    //The vertex definition
    struct Vertex {
        //Base constructors
        Vertex() : position(0.0f, 0.0f, 0.0f), color(), uv(0, 0) { }
        Vertex(Position pos, ColorRGBA8 Color, UV Uv) : 
            position(pos), color(Color), uv(Uv) { }
        Vertex(float x, float y, float z, ColorRGBA8 Color, UV Uv) : 
            position(x, y, z), color(Color), uv(Uv) { }
        Vertex(float x, float y, float z, GLubyte r, GLubyte g, GLubyte b, GLubyte a, UV Uv) : 
            position(x, y, z), color(r, g, b, a), uv(Uv) { }
        Vertex(float x, float y, float z, GLubyte r, GLubyte g, GLubyte b, GLubyte a, float u, float v) :
            position(x, y, z), color(r, g, b, a), uv(u, v) { }

        //This is the position struct. When you store a struct or class
        //inside of another struct or class, it is called composition. This is
        //layed out exactly the same in memory as if we had a float position[2],
        //but doing it this way makes more sense.
        Position position;

        //4 bytes for r g b a color.
        ColorRGBA8 color;

        //UV texture coordinates.
        UV uv;

        void setPosition(float x, float y) {
            position.x = x;
            position.y = y;
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
    };

}