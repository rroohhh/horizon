#pragma once
#include <gtkmm.h>
#include "canvas/canvas.hpp"

namespace horizon {

	class MainWindow: public Gtk::Window {
		public:
			MainWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& x);
			static MainWindow* create();
			CanvasGL *canvas = nullptr;
			Gtk::Label *active_tool_label = nullptr;
			Gtk::Label *tool_hint_label = nullptr;
			Gtk::Label *cursor_label = nullptr;
			Gtk::Box *left_panel = nullptr;
			Gtk::Box *top_panel = nullptr;
			Gtk::Viewport *property_viewport = nullptr;

			void tool_bar_set_visible(bool v);
			void tool_bar_set_tool_name(const std::string &s);
			void tool_bar_set_tool_tip(const std::string &s);
			void tool_bar_flash(const std::string &s);

			//virtual ~MainWindow();
		private :

			Gtk::Box *gl_container = nullptr;
			Gtk::Revealer *tool_bar = nullptr;
			Gtk::Label *tool_bar_name_label = nullptr;
			Gtk::Label *tool_bar_tip_label = nullptr;
			Gtk::Label *tool_bar_flash_label = nullptr;
			Gtk::Stack *tool_bar_stack = nullptr;
			sigc::connection tip_timeout_connection;
			bool tool_bar_queue_close = false;
			

			void sc(void);
			void cm(const horizon::Coordi &cursor_pos);
			

	};
}
