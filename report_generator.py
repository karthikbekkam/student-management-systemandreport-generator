import csv

students = []

# Read CSV safely
try:
    with open("students.csv", "r") as file:
        reader = csv.reader(file)
        for row in reader:
            if len(row) == 3:
                name = row[1]
                marks = int(row[2])
                students.append((name, marks))
except FileNotFoundError:
    print("students.csv file not found!")
    exit()

if len(students) == 0:
    print("No student records available!")
    exit()

marks = [m[1] for m in students]

def grade(m):
    if m >= 90: return "A"
    elif m >= 75: return "B"
    elif m >= 60: return "C"
    elif m >= 40: return "D"
    else: return "F"

topper = max(students, key=lambda x: x[1])
passed = len([m for m in marks if m >= 40])
failed = len(marks) - passed
avg = sum(marks) / len(marks)

if avg >= 75:
    performance = "Excellent"
elif avg >= 60:
    performance = "Good"
elif avg >= 40:
    performance = "Average"
else:
    performance = "Needs Improvement"

# Console output
print("\n--- Student Report ---")
print("Total Students :", len(students))
print("Average Marks  :", round(avg, 2))
print("Highest Marks  :", max(marks))
print("Lowest Marks   :", min(marks))
print(f"Topper         : {topper[0]} ({topper[1]})")
print("Passed         :", passed)
print("Failed         :", failed)
print("Class Performance :", performance)

# Export report to file
with open("final_report.txt", "w") as f:
    f.write("STUDENT REPORT SUMMARY\n")
    f.write("======================\n")
    f.write(f"Total Students : {len(students)}\n")
    f.write(f"Average Marks  : {round(avg,2)}\n")
    f.write(f"Highest Marks  : {max(marks)}\n")
    f.write(f"Lowest Marks   : {min(marks)}\n")
    f.write(f"Topper         : {topper[0]} ({topper[1]})\n")
    f.write(f"Passed         : {passed}\n")
    f.write(f"Failed         : {failed}\n")
    f.write(f"Class Performance : {performance}\n")

print("\nFinal report saved as final_report.txt")