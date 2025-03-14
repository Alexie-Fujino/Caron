import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

num_rows, num_cols = 10, 10  # 坐标大小
circle_radius = 0.05  # 球大小
mouse_radius = 0.4  # 鼠标范围
damping = 0.1  # 延时(平滑效果)

#初始化坐标轴
fig, ax = plt.subplots()
ax.set_xlim(-1, 1)
ax.set_ylim(-1, 1)
ax.set_xticks([])
ax.set_yticks([])
ax.set_aspect('equal')
fig.patch.set_facecolor('#171717')
ax.set_facecolor('#171717')

# 生成节点小球
x_vals = np.linspace(-0.8, 0.8, num_cols)
y_vals = np.linspace(-0.8, 0.8, num_rows)
points = np.array(np.meshgrid(x_vals, y_vals)).T.reshape(-1, 2)

# 存储动画
velocities = np.zeros_like(points)  # 流畅滑动
positions = points.copy()  # 实时位置

# 创建连线和球
circles = [plt.Circle(p, circle_radius, color='#f7f7f7', animated=True) for p in points]
centers = [plt.Circle(p, circle_radius / 5, color='#f7f7f7', animated=True) for p in points]
lines = [plt.Line2D([p[0], p[0]], [p[1], p[1]], color='#f7f7f7', lw=1.5, animated=True) for p in points]

for circle, center, line in zip(circles, centers, lines):
    ax.add_patch(circle)
    ax.add_patch(center)
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
            # 使得小球远离鼠标
            target_x = mouse_pos[0] + dx / distance * mouse_radius
            target_y = mouse_pos[1] + dy / distance * mouse_radius
        else:
            # 回到初始位置
            target_x, target_y = point

        # 调整朝向目标的速度
        velocities[i] += (np.array([target_x, target_y]) - positions[i]) * damping
        positions[i] += velocities[i]  # 更新位置

        # 速度平滑移动 (阻尼效果)
        velocities[i] *= 0.85

        # 更新环和小球位置
        circle.center = positions[i]
        line.set_data([point[0], positions[i][0]], [point[1], positions[i][1]])

    return circles + lines

# 创建动画
ani = animation.FuncAnimation(fig, update, frames=60, interval=30, blit=True)

plt.show()
