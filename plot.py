import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

file_path = 'cmake-build-debug/telemetry.csv'

# Создаем холст для отрисовки
fig, ax = plt.subplots(figsize=(10, 10))

def update(frame):
    ax.clear() # Очищаем старый кадр

    try:
        # Читаем лог, который прямо сейчас пишет C++
        data = pd.read_csv(file_path)

        if data.empty:
            return

        # Рисуем траектории и текущее положение
        for ferry_id, ferry_data in data.groupby('FerryID'):
            # Линия пути
            ax.plot(ferry_data['PosX'], ferry_data['PosY'], label=f'Ship {ferry_id}', alpha=0.6)
            # Точка текущего местоположения (последняя запись в логе)
            ax.scatter(ferry_data['PosX'].iloc[-1], ferry_data['PosY'].iloc[-1], s=100, zorder=5)

        # Рисуем порт
        ax.scatter(1500, 5000, color='red', s=200, marker='*', label='Port (1500, 5000)', zorder=5)

        ax.set_title('IRT Ferry Simulator - LIVE DASHBOARD')
        ax.set_xlabel('X position (meters)')
        ax.set_ylabel('Y position (meters)')
        ax.grid(True, linestyle='--', alpha=0.7)
        ax.legend(loc='upper left')

        # Жестко фиксируем границы камеры, чтобы она не прыгала за кораблями
        ax.set_xlim(-1000, 2000)
        ax.set_ylim(-1000, 5500)

    except (FileNotFoundError, pd.errors.EmptyDataError):
        pass # Если файл еще не создался, просто ждем

# Запускаем бесконечный цикл анимации (интервал 100 мс)
ani = FuncAnimation(fig, update, interval=100, cache_frame_data=False)
plt.show()