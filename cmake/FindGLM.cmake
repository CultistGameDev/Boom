set(GLM_FOUND false CACHE BOOL "GLM Found")
set(GLM_ROOT "" CACHE PATH "Root Directory of GLM")

find_path(GLM_INCLUDE_DIR
  NAMES "glm/glm.hpp"
  HINTS
  ${GLM_ROOT}/include
  "/usr/local/include/glm"
)

if(NOT GLM_INCLUDE_DIR OR GLM_INCLUDE_DIR MATCHES "NOTFOUND")
  set(GLM_FOUND false)
else()
  set(GLM_FOUND true)
  set(GLM_INCLUDE_DIRS ${GLM_INCLUDE_DIR})
endif()
