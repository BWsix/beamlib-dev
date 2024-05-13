#include "base.vert.glsl"

uniform mat4 prevModel;
uniform mat4 prevViewProjection;

out vec4 ClipSpacePos;
out vec4 PrevClipSpacePos;

void main() {
    mat4 mv = view * model;
    gl_Position = projection * mv * vec4(aPosition, 1.0);
    Position = vec3(mv * vec4(aPosition, 1.0));
    Normal = normalize(mat3(transpose(inverse(mv))) * aNormal);
    TexCoords = aTexCoords;

    ClipSpacePos = projection * mv * vec4(aPosition, 1.0);
    PrevClipSpacePos = prevViewProjection * prevModel * vec4(aPosition, 1.0);
}
