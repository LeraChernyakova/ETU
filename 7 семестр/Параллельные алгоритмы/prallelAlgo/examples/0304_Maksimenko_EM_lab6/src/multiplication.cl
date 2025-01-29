__kernel void multiply( const int lhs_w, const int common_size, const int rhs_h
                      , const __global int* lhs, const __global int* rhs, __global int* result )
{
    const int tile_size  = 16;

    const int tile_row   = get_local_id( 0 );
    const int tile_col   = get_local_id( 1 );
    const int global_row = get_group_id( 0 ) * tile_size + tile_row;
    const int global_col = get_group_id( 1 ) * tile_size + tile_col;

    /// Tile lhs and rhs memory
    __local int lhs_tile[ tile_size ][ tile_size ];
    __local int rhs_tile[ tile_size ][ tile_size ];

    int accumulator = 0;
    const int tiles_count = common_size / tile_size;
    for ( int i = 0; i < tiles_count; ++i )
    {
        /// Load tiles buffers
        const int tile_pos_row = tile_size * i + tile_row;
        const int tile_pos_col = tile_size * i + tile_col;
        lhs_tile[ tile_col ][ tile_row ] = lhs[ global_row + tile_pos_col * lhs_w ];
        rhs_tile[ tile_col ][ tile_row ] = rhs[ global_col * common_size + tile_pos_row ];

        /// Wait for tile is loaded
        barrier( CLK_LOCAL_MEM_FENCE );

        /// Perform computation for a single tile
        for ( int k = 0; k < tile_size; ++k )
        {
            accumulator += lhs_tile[ k ][ tile_row ] * rhs_tile[ tile_col ][ k ]; 
        }

        /// Synchronise before next tile load
        barrier( CLK_LOCAL_MEM_FENCE );
    }
    /// Store result
    result[ global_col * lhs_w + global_row ] = accumulator;
}
