%% Plot statistical inefficiency from saved data for r, P, U
hold on
plot(temperature, s_corr_E);
plot(temperature, s_block_E, 'r');
xlabel('temperature [K]', 'FontSize', textStorlek);
ylabel('statistical inefficiency','FontSize', textStorlek)
title('Statistical inefficiency - Energy', 'FontSize', textStorlek)
text=legend('Correlation function', 'Block average');
set(text, 'FontSize', legendStorlek);

figure
hold on
plot(temperature, s_corr_P);
plot(temperature, s_block_P, 'r');
xlabel('temperature [K]', 'FontSize', textStorlek);
ylabel('statistical inefficiency','FontSize', textStorlek)
title('Statistical inefficiency - Long range order parameter', 'FontSize', textStorlek)
text=legend('Correlation function', 'Block average');
set(text, 'FontSize', legendStorlek);

figure
hold on
plot(temperature, s_corr_r);
plot(temperature, s_block_r, 'r');
xlabel('temperature [K]', 'FontSize', textStorlek);
ylabel('statistical inefficiency','FontSize', textStorlek)
title('Statistical inefficiency - Short range order parameter', 'FontSize', textStorlek)
text=legend('Correlation function', 'Block average');
set(text, 'FontSize', legendStorlek);
