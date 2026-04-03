import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv('build/path_coupling.csv')

plt.figure(figsize=(10, 6))
plt.plot(data['t_fine'], data['x_fine'], 'k-', label='Fine Path (N=128)')
plt.plot(data['t_coarse'].dropna(), data['x_coarse'].dropna(), 'ro--', markersize=4, label='Coarse Path (N=64)')

plt.xlabel('Time (t)')
plt.ylabel('Asset Price (X)')
plt.title('Tight Coupling of Coarse and Fine Paths')
plt.legend()
plt.grid(True, linestyle=':', alpha=0.6)

plt.savefig('path_coupling_plot.png', dpi=300, bbox_inches='tight')
print("Saved path_coupling_plot.png")