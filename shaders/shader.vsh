attribute highp vec4 vertex;
//attribute highp vec4 vertices;
//attribute highp vec4 qt_MultiTexCoord0;

uniform highp mat4 ViewProjectionMatrix;
uniform highp mat4 ModelMatrix;
//varying highp vec4 qt_TexCoord0;

    //layout(location = 0) in vec4 position;

void main(void)
{
    //gl_Position = vertices;
    gl_Position = ViewProjectionMatrix * ModelMatrix * vertex;
    //qt_TexCoord0 = qt_MultiTexCoord0;
}
