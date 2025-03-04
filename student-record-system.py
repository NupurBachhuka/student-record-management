from tkinter import *
from tkinter import simpledialog, messagebox

# Node structure
class StudentNode:
    def __init__(self, roll_no, name, marks):
        self.roll_no = roll_no
        self.name = name
        self.marks = marks
        self.next = None

# Linked List class
class StudentList:
    def __init__(self):
        self.start = None

    def add_at_beginning(self, roll_no, name, marks):
        new_node = StudentNode(roll_no, name, marks)
        new_node.next = self.start
        self.start = new_node

    def add_at_end(self, roll_no, name, marks):
        new_node = StudentNode(roll_no, name, marks)
        if not self.start:
            self.start = new_node
        else:
            temp = self.start
            while temp.next:
                temp = temp.next
            temp.next = new_node

    def add_after(self, after_roll_no, roll_no, name, marks):
        temp = self.start
        while temp:
            if temp.roll_no == after_roll_no:
                new_node = StudentNode(roll_no, name, marks)
                new_node.next = temp.next
                temp.next = new_node
                return True
            temp = temp.next
        return False

    def add_before(self, before_roll_no, roll_no, name, marks):
        if not self.start:
            return False
        if self.start.roll_no == before_roll_no:
            self.add_at_beginning(roll_no, name, marks)
            return True
        temp = self.start
        while temp.next:
            if temp.next.roll_no == before_roll_no:
                new_node = StudentNode(roll_no, name, marks)
                new_node.next = temp.next
                temp.next = new_node
                return True
            temp = temp.next
        return False

    def delete_node(self, roll_no):
        if not self.start:
            return False
        if self.start.roll_no == roll_no:
            self.start = self.start.next
            return True
        temp = self.start
        while temp.next:
            if temp.next.roll_no == roll_no:
                temp.next = temp.next.next
                return True
            temp = temp.next
        return False

    def reverse(self):
        prev = None
        current = self.start
        while current:
            next_node = current.next
            current.next = prev
            prev = current
            current = next_node
        self.start = prev

    def count(self):
        count = 0
        temp = self.start
        while temp:
            count += 1
            temp = temp.next
        return count

    def search(self, roll_no):
        temp = self.start
        while temp:
            if temp.roll_no == roll_no:
                return f"Roll No: {temp.roll_no}, Name: {temp.name}, Marks: {temp.marks}"
            temp = temp.next
        return None

    def display(self):
        result = []
        temp = self.start
        while temp:
            result.append(f"Roll No: {temp.roll_no}, Name: {temp.name}, Marks: {temp.marks}")
            temp = temp.next
        return "\n".join(result) if result else "List is empty."

# Create an instance of StudentList
student_list = StudentList()

# GUI functions
def add_student_at_beginning():
    roll_no, name, marks = get_student_details()
    if roll_no:
        student_list.add_at_beginning(roll_no, name, marks)
        messagebox.showinfo("Success", "Student added at the beginning.")

def add_student_at_end():
    roll_no, name, marks = get_student_details()
    if roll_no:
        student_list.add_at_end(roll_no, name, marks)
        messagebox.showinfo("Success", "Student added at the end.")

def add_student_after():
    roll_no = simpledialog.askinteger("Input", "Enter Roll No of the student after whom to add:")
    if roll_no is not None:
        new_roll_no, name, marks = get_student_details()
        if student_list.add_after(roll_no, new_roll_no, name, marks):
            messagebox.showinfo("Success", "Student added successfully.")
        else:
            messagebox.showerror("Error", "Roll No not found.")

def add_student_before():
    roll_no = simpledialog.askinteger("Input", "Enter Roll No of the student before whom to add:")
    if roll_no is not None:
        new_roll_no, name, marks = get_student_details()
        if student_list.add_before(roll_no, new_roll_no, name, marks):
            messagebox.showinfo("Success", "Student added successfully.")
        else:
            messagebox.showerror("Error", "Roll No not found.")

def delete_student():
    roll_no = simpledialog.askinteger("Input", "Enter Roll No to delete:")
    if roll_no is not None:
        if student_list.delete_node(roll_no):
            messagebox.showinfo("Success", "Student deleted successfully.")
        else:
            messagebox.showerror("Error", "Roll No not found.")

def reverse_list():
    student_list.reverse()
    messagebox.showinfo("Success", "List reversed.")

def display_students():
    students = student_list.display()
    messagebox.showinfo("Student List", students)

def count_students():
    count = student_list.count()
    messagebox.showinfo("Count", f"Number of students: {count}")

def search_student():
    roll_no = simpledialog.askinteger("Input", "Enter Roll No to search:")
    if roll_no is not None:
        result = student_list.search(roll_no)
        if result:
            messagebox.showinfo("Search Result", result)
        else:
            messagebox.showerror("Error", "Student not found.")

def create_list():
    num_students = simpledialog.askinteger("Input", "Enter the number of students to add:")
    if num_students is not None and num_students > 0:
        for _ in range(num_students):
            roll_no, name, marks = get_student_details()
            if roll_no:
                student_list.add_at_end(roll_no, name, marks)
        messagebox.showinfo("Success", f"Created a list with {num_students} students.")
    else:
        messagebox.showerror("Error", "Invalid number of students.")

def get_student_details():
    roll_no = simpledialog.askinteger("Input", "Enter Roll No:")
    if roll_no is None:
        return None, None, None
    name = simpledialog.askstring("Input", "Enter Name:")
    if name is None:
        return None, None, None
    marks = simpledialog.askfloat("Input", "Enter Marks:")
    if marks is None:
        return None, None, None
    return roll_no, name, marks

# Main GUI window
root = Tk()
root.title("Student Management System")

Label(root, text="Student Management System", font=("Arial", 16)).pack(pady=10)

Button(root, text="Create List", command=create_list, width=20).pack(pady=5)
Button(root, text="Add at Beginning", command=add_student_at_beginning, width=20).pack(pady=5)
Button(root, text="Add at End", command=add_student_at_end, width=20).pack(pady=5)
Button(root, text="Add After", command=add_student_after, width=20).pack(pady=5)
Button(root, text="Add Before", command=add_student_before, width=20).pack(pady=5)
Button(root, text="Delete", command=delete_student, width=20).pack(pady=5)
Button(root, text="Reverse List", command=reverse_list, width=20).pack(pady=5)
Button(root, text="Display List", command=display_students, width=20).pack(pady=5)
Button(root, text="Count Students", command=count_students, width=20).pack(pady=5)
Button(root, text="Search Student", command=search_student, width=20).pack(pady=5)

root.mainloop()
