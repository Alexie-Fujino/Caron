import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

print("请输入磁力小球点阵形状(可选: square,circle,heart):")
shape_type = input()
num_rows, num_cols = 18, 18  # 网格边长
circle_radius = 0.05  # 球半径
mouse_radius = 0.4  # 鼠标范围
damping = 0.1  # 延时(平滑效果)

# 初始化坐标轴
fig, ax = plt.subplots()
ax.set_xlim(-1.5, 1.5)
ax.set_ylim(-1.5, 1.5)
ax.set_xticks([])
ax.set_yticks([])
ax.set_aspect('equal')
fig.patch.set_facecolor('#171717')
ax.set_facecolor('#171717')

# 生成网格点
x_vals = np.linspace(-1, 1, num_cols)
y_vals = np.linspace(-1, 1, num_rows)
grid_points = np.array(np.meshgrid(x_vals, y_vals)).T.reshape(-1, 2)

# 形状判定函数
def is_inside_shape(point, shape):
    x, y = point
    if shape == "square":
        return abs(x) <= 0.8 and abs(y) <= 0.8
    elif shape == "circle":
        return x**2 + y**2 <= 0.9
    elif shape == "heart":
        return (x**2 + y**2 - 0.25)**3 - x**2 * y**3 <= 0
    return False

# 筛选符合形状的点
filtered_points = np.array([p for p in grid_points if is_inside_shape(p, shape_type)])

# 仅保留符合形状的点
points = filtered_points.copy()
velocities = np.zeros_like(points)
positions = points.copy()

# 生成小球和连线
circles = [plt.Circle(p, circle_radius, color='#f7f7f7', animated=True) for p in points]
lines = [plt.Line2D([p[0], p[0]], [p[1], p[1]], color='#f7f7f7', lw=1.5, animated=True) for p in points]

for circle, line in zip(circles, lines):
    ax.add_patch(circle)
    ax.add_line(line)

# 鼠标位置 (默认屏幕外)
mouse_pos = np.array([-2, -2])

def on_mouse_move(event):
    global mouse_pos
    if event.xdata is not None and event.ydata is not None:
        mouse_pos = np.array([event.xdata, event.ydata])
    else:
        mouse_pos = np.array([-2, -2])

fig.canvas.mpl_connect('motion_notify_event', on_mouse_move)

def update(frame):
    global velocities, positions

    for i, (point, circle, line) in enumerate(zip(points, circles, lines)):
        dx, dy = point - mouse_pos
        distance = np.sqrt(dx**2 + dy**2)

        if distance < mouse_radius:
            # 远离鼠标
            target_x = mouse_pos[0] + dx / distance * mouse_radius
            target_y = mouse_pos[1] + dy / distance * mouse_radius
        else:
            # 回到原始位置
            target_x, target_y = point

        # 计算速度
        velocities[i] += (np.array([target_x, target_y]) - positions[i]) * damping
        positions[i] += velocities[i]
        velocities[i] *= 0.85  # 速度衰减

        # 更新位置
        circle.center = positions[i]
        line.set_data([point[0], positions[i][0]], [point[1], positions[i][1]])

    return circles + lines

# 创建动画
ani = animation.FuncAnimation(fig, update, frames=60, interval=30, blit=True)

plt.show()
