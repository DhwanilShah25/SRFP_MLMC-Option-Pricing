import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# Load benchmark data
data = pd.read_csv('build/complexity_data.csv')

eps = data['epsilon']
time_std = data['std_mc_time']
time_mlmc = data['mlmc_time']

# The paper scales the cost by epsilon^2 to prove the theoretical bounds
cost_std_scaled = time_std * (eps ** 2)
cost_mlmc_scaled = time_mlmc * (eps ** 2)

plt.figure(figsize=(8, 5))

plt.plot(eps, cost_std_scaled, 'k*-', label='Std MC')
plt.plot(eps, cost_mlmc_scaled, 'k*--', label='MLMC')

plt.xscale('log')
plt.yscale('log')
plt.gca().invert_xaxis() # Smaller epsilon on the right

plt.xlabel('Accuracy $\epsilon$')
plt.ylabel('Cost $\epsilon^2$')
plt.title('Computational Cost Scaled by $\epsilon^2$ (Figure 3 Recreation)')
plt.legend()
plt.grid(True, which="both", ls="--", alpha=0.5)

# plt.show()
plt.savefig('complexity_plot.png', dpi=300, bbox_inches='tight')
print("Saved complexity_plot.png")