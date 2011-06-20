uniform sampler2D frame;
uniform float frameWidth;

void main(void)
{
    vec4 sum = vec4(0.0);

    float blurSize = 1.0 / frameWidth;

    sum += texture2D(frame, vec2(gl_TexCoord[0].x - 3.0 * blurSize, gl_TexCoord[0].y)) * 0.09;
    sum += texture2D(frame, vec2(gl_TexCoord[0].x - 2.0 * blurSize, gl_TexCoord[0].y)) * 0.12;
    sum += texture2D(frame, vec2(gl_TexCoord[0].x - blurSize, gl_TexCoord[0].y)) * 0.15;
    sum += texture2D(frame, vec2(gl_TexCoord[0].x, gl_TexCoord[0].y)) * 0.16;
    sum += texture2D(frame, vec2(gl_TexCoord[0].x + blurSize, gl_TexCoord[0].y)) * 0.15;
    sum += texture2D(frame, vec2(gl_TexCoord[0].x + 2.0 * blurSize, gl_TexCoord[0].y)) * 0.12;
    sum += texture2D(frame, vec2(gl_TexCoord[0].x + 3.0 * blurSize, gl_TexCoord[0].y)) * 0.09;

    gl_FragColor = sum;
}
