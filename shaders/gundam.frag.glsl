#include "base.frag.glsl"
#include "toon.glsl"

layout(location=0) out vec4 color;
layout(location=2) out vec4 motion;

uniform sampler2D depthTex;

in vec4 ClipSpacePos;
in vec4 PrevClipSpacePos;

uniform bool reflectionMode;
uniform bool toon;

void main() {
    if (reflectionMode && Position.y < 0){
        discard;
    }

    vec3 lightDir = normalize(lightPos - Position);
    vec3 normal = normalize(Normal);
    vec3 reflectDir = reflect(-lightDir, normal);

    float ambientIntensity = 0.3;
    vec3 ambient = ambientIntensity * lighting.diffuse;
    // vec3 ambient = ambientIntensity * vec3(texture(material.texture_diffuse1, TexCoords));

    float diffuseIntensity = max(0.0, dot(normal, lightDir));
    float diff = 0.5;
    vec3 diffuse = diff * diffuseIntensity * lighting.diffuse;
    // vec3 diffuse = diffuseIntensity * vec3(texture(material.texture_diffuse1, TexCoords));

    vec3 viewDir = normalize(viewPos - Position);
    float spec = 0.5;
    float specularIntensity = pow(max(0.0, dot(viewDir, reflectDir)), 32);
    vec3 specular = spec * specularIntensity * lighting.diffuse;
    // vec3 specular = specularIntensity * vec3(texture(material.texture_specular1, TexCoords));

    float shadow = ShadowCalculation(depthTex, LightSpacePosition);
    vec3 result = ambient + (1.0 - shadow) * (diffuse + specular);

    float gamma = 2.2;
    color = vec4(pow(result, vec3(gamma)), 1.0);
    if (toon) {
        float intensity = max(dot(normal, lightDir), 0.0);

        if (intensity > 0.95) {
            color.rgb = lighting.diffuse * vec3(1.0);
        } else if (intensity > 0.7){ 
            color.rgb = lighting.diffuse * vec3(0.9);
        } else if (intensity > 0.5) {
            color.rgb = lighting.diffuse * vec3(0.6);
        } else {
            color.rgb = lighting.diffuse * vec3(0.3);
        }
    }

    vec3 NDCPos = (ClipSpacePos / ClipSpacePos.w).xyz;
    vec3 PrevNDCPos = (PrevClipSpacePos / PrevClipSpacePos.w).xyz;
    motion = vec4((NDCPos - PrevNDCPos).xy, 101, 1.0);
}
