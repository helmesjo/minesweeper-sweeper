#pragma once

namespace helmesjo {

	class Grid {
	public:
		Grid(int nrColumns, int nrRows);

	private:
		unsigned int nrColumns = 0, nrRows = 0;
	};

}
