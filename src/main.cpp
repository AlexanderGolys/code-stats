#include "filesystemTests.hpp"
#include "logging.hpp"

int main()
  {
    logging::Logger::init();
    Path p = Path(filesystem::current_path().parent_path().parent_path().parent_path().parent_path() / "src");
    CppProject project = CppProject(p);
    auto files = project.listAllCppFiles({});
  }
