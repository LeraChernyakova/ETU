__kernel void multiply( 
	const int l_n, const int c_n, const int r_n, 
	const __global int* l_mat, const __global int* r_mat, __global int* result )
{
    const int tile_size  = 16;

    const int tile_row = get_local_id( 0 );
    const int tile_col = get_local_id( 1 );
    const int global_row = get_group_id( 0 ) * tile_size + tile_row;
    const int global_col = get_group_id( 1 ) * tile_size + tile_col;

    __local int l_mat_tile[ tile_size ][ tile_size ];
    __local int r_mat_tile[ tile_size ][ tile_size ];

    int accumulator = 0;
    const int tiles_count = c_n / tile_size;
    for ( int i = 0; i < tiles_count; ++i )
    {
        const int tile_pos_row = tile_size * i + tile_row;
        const int tile_pos_col = tile_size * i + tile_col;
        l_mat_tile[ tile_col ][ tile_row ] = l_mat[ global_row + tile_pos_col * l_n ];
        r_mat_tile[ tile_col ][ tile_row ] = r_mat[ global_col * c_n + tile_pos_row ];

        barrier( CLK_LOCAL_MEM_FENCE );

        for ( int k = 0; k < tile_size; ++k )
        {
            accumulator += l_mat_tile[ k ][ tile_row ] * r_mat_tile[ tile_col ][ k ]; 
        }

        barrier( CLK_LOCAL_MEM_FENCE );
    }
    result[ global_col * l_n + global_row ] = accumulator;
}
