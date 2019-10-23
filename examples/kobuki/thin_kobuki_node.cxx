#include "ros_util.h"
#include "thin_kobuki_node.h"

namespace kobuki
{
    KobukiNode::KobukiNode(int argc, char* argv[]) 
    : context(rcl_get_zero_initialized_context()), node(rcl_get_zero_initialized_node()) {
        rcl_init_options_t init_options;    //global static var in rcl
        rcl_ret_t          rc;
        init_options = rcl_get_zero_initialized_init_options();
        rc = rcl_init_options_init(&init_options, rcl_get_default_allocator());
        if (rc != RCL_RET_OK) {
            throw RCLException(rcutils_get_error_string().str);
        }

        rc = rcl_init(argc, argv, &init_options, &context);
        rcl_init_options_fini(&init_options);
        if (rc != RCL_RET_OK) {
            throw RCLException(rcutils_get_error_string().str);
        }

        rcl_node_options_t node_ops = rcl_node_get_default_options();

        rc = rcl_node_init(&node, "uros_kobuki_node", "", &context, &node_ops);
        if (rc != RCL_RET_OK) {
            throw RCLException(rcutils_get_error_string().str);
        }
    }

    KobukiNode::~KobukiNode() {
        rcl_node_fini( &node);
    }
}