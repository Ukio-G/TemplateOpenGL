#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 vColor;
out vec2 TexCoord;

uniform mat4 transform;
uniform mat4 projection;

void main()
{
    vec4 pos = transform * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    pos = projection * pos;
    gl_Position = pos;
    vColor = aColor;
    TexCoord = aTexCoord;
}
