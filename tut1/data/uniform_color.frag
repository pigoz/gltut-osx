#version 330
out vec4 outputColor;
void main()
{
    float lerpValue = gl_FragCoord.y / 500.0f;
    vec4 white      = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    vec4 darkgray   = vec4(0.2f, 0.2f, 0.2f, 1.0f);

    outputColor = mix(white, darkgray, lerpValue);
}
