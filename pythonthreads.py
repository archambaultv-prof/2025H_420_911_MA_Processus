import threading
import time


def worker(thread_id, sleep_time):
    """Function that will be executed by each thread"""
    print(f"Thread {thread_id} starting...")
    time.sleep(sleep_time)
    print(f"Thread {thread_id} finished after {sleep_time} seconds")


# Create multiple threads
threads = []
for i in range(3):
    # Create a thread with different sleep times
    t = threading.Thread(target=worker, args=(i + 1, (i + 1) * 2))
    threads.append(t)
    t.start()

# Wait for all threads to complete
for t in threads:
    t.join()

print("All threads completed!")
