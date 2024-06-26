/*
 * libaudqt.h
 * Copyright 2014 Ariadne Conill
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions, and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions, and the following disclaimer in the documentation
 *    provided with the distribution.
 *
 * This software is provided "as is" and without any warranty, express or
 * implied. In no event shall the authors be liable for any damages arising from
 * the use of this software.
 */

#ifndef LIBAUDQT_H
#define LIBAUDQT_H

#include <QFileDialog>
#include <QMargins>
#include <QMessageBox>
#include <QString>
#include <libaudcore/objects.h>

class QBoxLayout;
class QHBoxLayout;
class QIcon;
class QLayout;
class QLineEdit;
class QPixmap;
class QProxyStyle;
class QToolButton;
class QVBoxLayout;
class QWidget;

enum class PluginType;
class Playlist;
class PluginHandle;
struct PreferencesWidget;

namespace audqt
{

enum class FileMode
{
    Open,
    OpenFolder,
    Add,
    AddFolder,
    ImportPlaylist,
    ExportPlaylist,
    count
};

struct PixelSizes
{
    int OneInch;
    int TwoPt;
    int FourPt;
    int EightPt;
};

struct PixelMargins
{
    QMargins TwoPt;
    QMargins FourPt;
    QMargins EightPt;
};

struct MenuItem;

/* about.cc */
void aboutwindow_show();
void aboutwindow_hide();

/* playlist-management.cc */
void playlist_show_rename(Playlist playlist);
void playlist_confirm_delete(Playlist playlist);

/* equalizer.cc */
void equalizer_show();
void equalizer_hide();

/* eq-preset-qt.cc */
void eq_presets_show();
void eq_presets_hide();

/* fileopener.cc */
void fileopener_show(FileMode mode);

/* url-opener.cc */
void urlopener_show(bool open);

/* audqt.cc */
extern const PixelSizes & sizes;
extern const PixelMargins & margins;

static inline int to_native_dpi(int x)
{
    return aud::rescale(x, 96, sizes.OneInch);
}
static inline int to_portable_dpi(int x)
{
    return aud::rescale(x, sizes.OneInch, 96);
}

void init();
void cleanup();

QGradientStops dark_bg_gradient(const QColor & base);
QColor vis_bar_color(const QColor & hue, int bar, int n_bars);

QHBoxLayout * make_hbox(QWidget * parent, int spacing = sizes.FourPt);
QVBoxLayout * make_vbox(QWidget * parent, int spacing = sizes.FourPt);
void setup_proxy_style(QProxyStyle * style);

void enable_layout(QLayout * layout, bool enabled);
void clear_layout(QLayout * layout);
void window_bring_to_front(QWidget * win);
void simple_message(const char * title, const char * text);
void simple_message(const char * title, const char * text,
                    QMessageBox::Icon icon);
QString translate_str(const char * str, const char * domain);

#ifdef PACKAGE
static inline QString translate_str(const char * str)
{
    return translate_str(str, PACKAGE);
}
#endif

/* file-entry.cc */
QLineEdit * file_entry_new(QWidget * parent, const char * title,
                           QFileDialog::FileMode file_mode,
                           QFileDialog::AcceptMode accept_mode);
String file_entry_get_uri(QLineEdit * entry);
void file_entry_set_uri(QLineEdit * entry, const char * uri);

/* font-entry.cc */
QLineEdit * font_entry_new(QWidget * parent, const char * font);
QFont qfont_from_string(const char * name);
StringBuf qfont_to_string(const QFont & font);

/* prefs-builder.cc */
void prefs_populate(QBoxLayout * layout, ArrayRef<PreferencesWidget> widgets,
                    const char * domain);

/* prefs-plugin.cc */
void plugin_about(PluginHandle * ph);
void plugin_prefs(PluginHandle * ph);

/* prefs-window.cc */
void prefswin_show();
void prefswin_hide();
void prefswin_show_page(int id, bool show = true);
void prefswin_show_plugin_page(PluginType type);

/* song-window-qt.cc */
void songwin_show();
void songwin_hide();

/* log-inspector.cc */
void log_inspector_show();
void log_inspector_hide();

/* art-qt.cc */
QImage art_request(const char * filename, bool * queued = nullptr);
QPixmap art_scale(const QImage & image, unsigned int w, unsigned int h,
                  bool want_hidpi = true);
QPixmap art_request(const char * filename, unsigned int w, unsigned int h,
                    bool want_hidpi = true);
QPixmap art_request_current(unsigned int w, unsigned int h,
                            bool want_hidpi = true);

/* infopopup-qt.cc */
void infopopup_show(Playlist playlist, int entry);
void infopopup_show_current();
void infopopup_hide();

/* infowin.cc */
void infowin_show(Playlist playlist, int entry);
void infowin_show_selected(Playlist playlist);
void infowin_show_current();
void infowin_hide();

/* queue-manager.cc */
void queue_manager_show();
void queue_manager_hide();

/* volumebutton.cc */
QToolButton * volume_button_new(QWidget * parent = nullptr);

} // namespace audqt

#endif
