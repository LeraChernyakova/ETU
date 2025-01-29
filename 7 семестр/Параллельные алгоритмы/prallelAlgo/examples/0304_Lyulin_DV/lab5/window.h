#ifndef _PA_WINDOW_H
#define _PA_WINDOW_H

#include <FL/Fl.H>
#include <FL/Fl_Gl_Window.H>

#include <GL/glew.h>

#include <memory>

class Window : public Fl_Gl_Window
{
public:
	Window( int width, int height, const char *title = nullptr );
	~Window();

	int handle( int event );
	void set_buffer( const uint8_t *buffer, size_t width, size_t height );

protected:
	void draw();

private:
	void init();

private:
	size_t image_width_;
	size_t image_height_;
	const uint8_t *buffer_;

	GLuint texture_;
	GLuint shader_;
	GLuint vao_;
	GLuint vbo_;

};

#endif // #ifndef _PA_WINDOW_H