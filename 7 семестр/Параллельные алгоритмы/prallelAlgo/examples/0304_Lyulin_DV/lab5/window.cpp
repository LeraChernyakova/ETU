#include <window.h>

#include <stdexcept>
#include <cstdio>

namespace
{

void draw_error_callback( GLenum source, GLenum type, GLuint id, GLenum severity,
     GLsizei length,  const GLchar* message, const void* userParam )
{
     std::fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
          ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
          type, severity, message );
}

const char *vertexShader = R"(
#version 330 core
in vec2 pos;
out vec2 texCoord;
void main()
{
     gl_Position = vec4( pos, 0.0, 1.0 );
     texCoord = pos * 0.5 + 0.5;
}
)";

const char *fragmentShader = R"(
#version 330 core
in vec2 texCoord;
uniform sampler2D image;
void main()
{
     gl_FragColor = texture2D( image, texCoord );
}
)";

} // anonymous namespace

Window::Window( int width, int height, const char* title ):
     Fl_Gl_Window( width, height, title),
     image_width_{ 0 }, image_height_{ 0 }, buffer_{ nullptr },
     texture_{ 0 }, shader_{ 0 }, vao_{ 0 }, vbo_{ 0 }
{
     mode( FL_RGB8 | FL_DOUBLE | FL_OPENGL3 | FL_ALPHA );
}


Window::~Window()
{
     glBindBuffer( GL_ARRAY_BUFFER, 0 );
     glBindVertexArray( 0 );
     glUseProgram( 0 );
     glDeleteBuffers( 1, &vbo_ );
     glDeleteProgram( shader_ );
     if ( texture_ )
     {
          glDeleteTextures( 1, &texture_ );
     }
     glDeleteVertexArrays( 1, &vao_ );
}


int Window::handle( int event )
{
     static bool first = true;
     if ( first && event == FL_SHOW && shown() )
     {
          first = false;
          make_current();
          if ( glewInit() != GLEW_OK || !GLEW_VERSION_3_3 )
          {
               throw std::runtime_error{ "Failed to initialize GLEW" };
          }
          init();   // call only after context creation
     }
     return Fl_Gl_Window::handle( event );
}


void Window::set_buffer( const uint8_t *buffer, size_t width, size_t height )
{
     if ( !buffer )
     {
          return;
     }
     image_width_ = width;
     image_height_ = height;
     buffer_ = buffer;

     if ( texture_ != 0 )
     {
          glBindTexture( GL_TEXTURE_2D, 0 );
          glDeleteTextures( 1, &texture_ );
          texture_ = 0;
     }
     glGenTextures( 1, &texture_ );
     glBindTexture( GL_TEXTURE_2D, texture_ );
     glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
     glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, image_width_, image_height_, 0, GL_RGB, GL_UNSIGNED_BYTE, buffer_ );
     glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
     glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
     glActiveTexture( GL_TEXTURE0 );
     glUniform1i( glGetUniformLocation( shader_, "image" ), 0 );

     if ( shown() )
     {
          redraw();
     }
}


void Window::draw()
{
     if ( !valid() )
     {
          glViewport( 0, 0, pixel_w(), pixel_h() );
     }
     glClearColor( 0, 0, 0, 0 );
     glClear( GL_COLOR_BUFFER_BIT );
     if ( buffer_ )
     {
          glDrawArrays( GL_TRIANGLE_STRIP, 0, 4 );
     }
}

void Window::init()
{
     constexpr float verts[ 4 ][ 2 ] =
     {
          { -1.0f, -1.0f },
          {  1.0f, -1.0f },
          { -1.0f,  1.0f },
          {  1.0f,  1.0f }
     };
     glGenVertexArrays( 1, &vao_ );
     glBindVertexArray( vao_ );
     glEnable( GL_DEBUG_OUTPUT );
     glDebugMessageCallback( draw_error_callback, 0 );
     shader_ = glCreateProgram();

     GLuint handle = glCreateShader( GL_VERTEX_SHADER );
     glShaderSource( handle, 1, &vertexShader, 0 );
     glCompileShader( handle );
     glAttachShader( shader_, handle );
     glDeleteShader( handle );

     handle = glCreateShader( GL_FRAGMENT_SHADER );
     glShaderSource( handle, 1, &fragmentShader, 0 );
     glCompileShader( handle );
     glAttachShader( shader_, handle );
     glDeleteShader( handle );

     glLinkProgram( shader_ );
     glValidateProgram( shader_ );
     glUseProgram( shader_ );

     glGenBuffers( 1, &vbo_ );
     glBindBuffer( GL_ARRAY_BUFFER, vbo_ );
     glBufferData( GL_ARRAY_BUFFER, sizeof( verts ), &verts[ 0 ][ 0 ], GL_STATIC_DRAW );

     glEnableVertexAttribArray( 0 );
     glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, sizeof( float ) * 2, 0 );
}
