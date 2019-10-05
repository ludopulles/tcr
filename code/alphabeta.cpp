ll negamax( board_t& node, ll depth = INF, ll turn = 1, ll a = -INF, ll b = INF ) {
	vector<board_t> moves;
	getMoves( node, moves );
	ll best = -INF;
	ll temp;
	if( moves.empty() || depth == 0 )
		return score( node, turn );
	for( auto& move : moves ) {
		temp = -negamax( move, depth - 1, turn + 1, -b, -a );
		best = max( temp, best );
		a = max( a, temp );
		if( a >= b )
			break;
	}
	return best;
}