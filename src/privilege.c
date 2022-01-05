#include <myfsconfig.h>

#include <myfsapi.h>

size_t uid, gid;

MYFS_EXPORT uint8_t grant_privilege(const MYFILE_ATTRIBUTE* file)
{
    if (file->uid == uid) {
        return file->owner;
    }
    if (file->gid == gid) {
        return file->group;
    }
    return file->other;
}
