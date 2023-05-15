function [j_index, k_index] = unstacking_single(i_index, param)
    k_index = rem(i_index, param.N);
    if k_index == 0
        k_index = param.N;
    end
    j_index = ( i_index - k_index )/param.N + 1;
end