import tkinter as tk
from tkinter import ttk

# Create the main window
programmer_window = tk.Tk()
programmer_window.title("Programmer Interface")
programmer_window.geometry("500x350")  # Set the window size

# Style configuration
style = ttk.Style(programmer_window)
style.configure('TFrame', background='#f0f0f0')
style.configure('TButton', background='#e1e1e1', font=('Helvetica', 10))
style.configure('TLabelFrame', background='#f0f0f0', font=('Helvetica', 12, 'bold'))
style.configure('TLabel', background='#f0f0f0', font=('Helvetica', 10))

# Add a frame for Task Viewing
task_viewing_frame = ttk.LabelFrame(programmer_window, text="Your Tasks")
task_viewing_frame.grid(row=1, column=0, padx=10, pady=10, sticky="ew")

# Scrollbar for listbox
scrollbar = ttk.Scrollbar(task_viewing_frame, orient="vertical")

# Listbox to display tasks with a scrollbar
tasks_listbox = tk.Listbox(task_viewing_frame, height=10, yscrollcommand=scrollbar.set)
scrollbar.config(command=tasks_listbox.yview)
scrollbar.grid(row=0, column=1, sticky='ns')
tasks_listbox.grid(row=0, column=0, padx=10, pady=10, sticky="ew")

# Dummy tasks for a programmer
dummy_tasks_programmer = ["1. Improve UI", "- Due Date: 2023-07-20"]
for task in dummy_tasks_programmer:
    tasks_listbox.insert(tk.END, task)

# Labels for Project Name and Team Lead Name
project_name_label = ttk.Label(programmer_window, text="Project Name: Project Alpha", font=('Helvetica', 20, 'bold'))
project_name_label.grid(row=0, column=0, padx=10, pady=5, sticky="w")

team_lead_name_label = ttk.Label(programmer_window, text="Team Lead: Ramesh Tiwari", font=('Helvetica', 20, 'bold'))
team_lead_name_label.grid(row=2, column=0, padx=10, pady=5, sticky="w")

# Run the application
programmer_window.mainloop()
