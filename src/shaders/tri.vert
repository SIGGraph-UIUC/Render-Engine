#version 450

layout(location = 0) out vec3 frag_color;

#ifdef gl_VertexIndex
#define VERTEXID gl_VertexIndex
#else
#define VERTEXID gl_VertexID
#endif


void main() {
    switch (VERTEXID) {
        case 0:
            gl_Position = vec4(0.0, 0.0, 0.0, 1.0);
            break;
        case 1:
            gl_Position = vec4(1.0, 1.0, 0.0, 1.0);
            break;
        case 2:
            gl_Position = vec4(0.0, 1.0, 0.0, 1.0);
            break;
    }

    frag_color = vec3(1.0,0.0,0.0);
}