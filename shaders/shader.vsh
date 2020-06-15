//attribute highp vec4 qt_Vertex;
attribute highp vec4 vertices;
//attribute highp vec4 qt_MultiTexCoord0;
//uniform highp mat4 qt_ModelViewProjectionMatrix;
//varying highp vec4 qt_TexCoord0;

    //layout(location = 0) in vec4 position;

void main(void)
{
    gl_Position = vertices;
    //gl_Position = qt_ModelViewProjectionMatrix * qt_Vertex;
    //qt_TexCoord0 = qt_MultiTexCoord0;
}
