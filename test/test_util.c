/*!gcc -ansi -pedantic-errors {0} -I../include/ -I./include/ -I. -o out.exe; ./out.exe */

#include <exotic/cester.h>
#include <konfiger_util.h>

CESTER_BODY(
static char extra_escape[] = {
    '~'
};
)

CESTER_TEST(test_check_escape_and_unescape_seperator, _,
    char *actual_str = "\\,Hello~W\n-\t-\torld";
    char *t1 = escape_string(actual_str, extra_escape);
    char *t2 = un_escape_string(actual_str, NULL);
    
    cester_assert_str_not_equal(actual_str, t1);
    cester_assert_str_equal(t1, "\\,Hello^~W\n-\t-\torld");
    cester_assert_str_not_equal(t1, un_escape_string(t1, extra_escape));
    cester_assert_str_not_equal(actual_str, un_escape_string(t1, NULL));
    cester_assert_str_equal(un_escape_string(t1, extra_escape), actual_str);
    
    cester_assert_str_not_equal(t1, t2);
    cester_assert_str_equal(t2, "\\,Hello~W\n-\t-\torld");
    cester_assert_str_not_equal(t2, un_escape_string(t1, NULL));
    cester_assert_str_equal(actual_str, un_escape_string(t2, NULL));
    cester_assert_str_equal(un_escape_string(t1, extra_escape), actual_str);
)

CESTER_OPTIONS(
    CESTER_VERBOSE();
    CESTER_MINIMAL();
)
