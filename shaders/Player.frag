uniform sampler2D texture;
void main() {
    // lookup the pixel in the texture
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);

    // multiply it by the color
    vec3 rgb = gl_Color.xyz;
    gl_FragColor = vec4(rgb * pixel.xyz + sin(distance(pixel, vec4(0.))) / 10., pixel.a);
}