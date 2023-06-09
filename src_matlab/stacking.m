function i_index = stacking(j_index, k_index, param)
    N = param.N;
    i_index = N*(j_index - 1) + k_index;
end