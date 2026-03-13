import pandas as pd
import matplotlib.pyplot as plt

file_path = 'cmake-build-debug/telemetry.csv'
try:
    data = pd.read_csv(file_path)

    plt.figure(figsize=(10, 10))

    # Ferry trajectory
    plt.plot(data['PosX'], data['PosY'], label = 'Ferry Trajectory', color = 'blue', linewidth = 2)

    # Start point
    plt.scatter(data['PosX'].iloc[0], data['PosY'].iloc[0], color = 'green', s = 100, label = 'Start', zorder = 5)

    # finish point
    plt.scatter(data['PosX'].iloc[-1], data['PosY'].iloc[-1], color = 'orange', s = 100, label = 'Stop', zorder = 5)

    # goal port
    plt.scatter(1500, 5000, color = 'red', s = 200, marker = '*', label = 'Target Port (1500, 5000)', zorder = 5)

    plt.title('IRT Ferry')
    plt.xlabel('X position (meters)')
    plt.ylabel('Y position (meters)')
    plt.grid(True, linestyle='--', alpha=0.7)
    plt.legend()
    plt.axis('equal')
    plt.show()
except FileNotFoundError:
    print(f"file {file_path} not found")
