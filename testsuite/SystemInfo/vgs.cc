
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE libstorage

#include <boost/test/unit_test.hpp>
#include <boost/algorithm/string.hpp>

#include "storage/SystemInfo/CmdLvm.h"
#include "storage/Utils/Mockup.h"
#include "storage/Utils/StorageDefines.h"


using namespace std;
using namespace storage;


void
check(const vector<string>& input, const vector<string>& output)
{
    Mockup::set_mode(Mockup::Mode::PLAYBACK);
    Mockup::set_command(VGSBIN " --noheadings --unbuffered --units b --nosuffix --options vg_name,"
			"vg_uuid,vg_extent_size,vg_extent_count", input);

    CmdVgs cmd_vgs;

    ostringstream parsed;
    parsed.setf(std::ios::boolalpha);
    parsed << cmd_vgs;

    string lhs = parsed.str();
    string rhs = boost::join(output, "\n");

    BOOST_CHECK_EQUAL(lhs, rhs);
}


BOOST_AUTO_TEST_CASE(parse1)
{
    vector<string> input = {
	"  system  OMPzXF-m3am-1zIl-AVdQ-i5Wx-tmyN-cevmRn 4194304 230400"
    };

    vector<string> output = {
	"vgs:<vg-name:system vg-uuid:OMPzXF-m3am-1zIl-AVdQ-i5Wx-tmyN-cevmRn extent-size:4194304 extent-count:230400>"
    };

    check(input, output);
}
