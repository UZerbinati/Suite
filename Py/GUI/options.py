from dearpygui.core import *
from dearpygui.simple import *
from math import cos

themes = ["Dark", "Light", "Classic", "Dark 2", "Grey", "Dark Grey", "Cherry", "Purple", "Gold", "Red"]
theme = "Dark";

def Change_Theme(sender,data):
    global theme;
    theme =  get_value("Style##1");
    log_info("Selected new theme: {}".format(theme));
def change_callback(sender,data):
    set_theme(theme);
    print("Options have been changed");
def show_plot(sender,data):
    delete_item("Signal_Plots");
    Signal_Plots();

def plot_callback(sender,data):
    # keeping track of frames
    frame_count = get_data("frame_count")
    frame_count += 1
    add_data("frame_count", frame_count)

    # updating plot data
    plot_datax = get_data("signalplot_datax")
    plot_datay = get_data("signalplot_datay")
    if len(plot_datax) > 2000:
        frame_count = 0
        plot_datax.clear()
        plot_datay.clear()
    plot_datax.append(3.14 * frame_count / 180)
    plot_datay.append(cos(3 * 3.14 * frame_count / 180))
    add_data("signalplot_datax", plot_datax)
    add_data("signalplot_datay", plot_datay)

    # plotting new data
    clear_plot("Signal_Plot")
    add_line_series("Singal_Plot", "Cos", plot_datax, plot_datay, weight=2)

def Options():
    with window("Options",height=600,width=200,x_pos=0,y_pos=0):
        add_text("The following options are avaiable,");
        add_spacing(count=5);
        with menu("Style"):
            add_combo("Style##1", items=themes, default_value=theme, callback=Change_Theme)
        with menu("Visual"):
            add_menu_item("Disply Logs", callback=show_logger)
            add_menu_item("Show Signal Plots", callback=show_plot);
        add_button("Change", callback=change_callback);
def Signal_Plots():
    with window("Signal_Plots",height=400,width=800,x_pos=200):
            add_plot("Singal_Plot", height=-1)
            add_data("signalplot_datax", [])
            add_data("signalplot_datay", [])
            add_data("frame_count", 0)
    set_render_callback(plot_callback);
Options();
start_dearpygui();
