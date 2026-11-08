import os
import time

# --------------------------配置区--------------------------
REPO_PATH = r"D:\CST"        # 你的仓库路径
COMMIT_MSG = "auto sync: files updated"
SYNC_INTERVAL = 300          # 同步间隔，单位秒，300=5分钟
BRANCH = "main"              # 如果你的分支名是master就改成master
MAX_RETRY = 2                # push失败重试次数
# ----------------------------------------------------------

def run_cmd(cmd):
    os.chdir(REPO_PATH)
    print(f"\n[执行] {cmd}")
    ret_code = os.system(cmd)
    return ret_code == 0

def git_sync():
    for attempt in range(MAX_RETRY + 1):
        print(f"\n===== 第 {attempt+1} 次同步尝试 =====")
        ok1 = run_cmd(f"git pull origin {BRANCH}")
        run_cmd("git add .")
        ok2 = run_cmd(f'git commit -m "{COMMIT_MSG}"')
        ok3 = run_cmd(f"git push origin {BRANCH}")
        if ok1 and ok3:
            print("✅同步成功！")
            return True
        else:
            print(f"❌同步失败，准备重试...")
            time.sleep(3)
    print("❌多次重试仍然同步失败")
    return False

if __name__ == "__main__":
    while True:
        git_sync()
        print(f"\n===== 等待 {SYNC_INTERVAL}s 后再次同步 =====")
        time.sleep(SYNC_INTERVAL)