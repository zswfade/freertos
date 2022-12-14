VERIFAST ?= verifast
VERIFAST_ARGS = -I include -c $(EXTRA_VERIFAST_ARGS)

ifeq ($(NO_COVERAGE), 1)
check_coverage = cat
else
check_coverage = perl -pe \
  'END { \
      if ($$status) { \
        print "Coverage regression failed: Expected $1 statements verified.\n"; \
      } \
      exit $$status; \
   } \
   $$status=/$1 statements verified/ ? 0 : 1;'
endif

all: queue list

.PHONY: queue
queue:
	@$(VERIFAST) $(VERIFAST_ARGS) -disable_overflow_check queue/create.c                    | $(call check_coverage,315)
	@$(VERIFAST) $(VERIFAST_ARGS)                         queue/prvCopyDataFromQueue.c      | $(call check_coverage,308)
	@$(VERIFAST) $(VERIFAST_ARGS) -disable_overflow_check queue/prvCopyDataToQueue.c        | $(call check_coverage,336)
	@$(VERIFAST) $(VERIFAST_ARGS)                         queue/prvIsQueueEmpty.c           | $(call check_coverage,289)
	@$(VERIFAST) $(VERIFAST_ARGS)                         queue/prvIsQueueFull.c            | $(call check_coverage,289)
	@$(VERIFAST) $(VERIFAST_ARGS)                         queue/prvLockQueue.c              | $(call check_coverage,290)
	@$(VERIFAST) $(VERIFAST_ARGS)                         queue/prvUnlockQueue.c            | $(call check_coverage,304)
	@$(VERIFAST) $(VERIFAST_ARGS)                         queue/uxQueueMessagesWaiting.c    | $(call check_coverage,292)
	@$(VERIFAST) $(VERIFAST_ARGS)                         queue/uxQueueSpacesAvailable.c    | $(call check_coverage,290)
	@$(VERIFAST) $(VERIFAST_ARGS)                         queue/vQueueDelete.c              | $(call check_coverage,287)
	@$(VERIFAST) $(VERIFAST_ARGS)                         queue/xQueueGenericSend.c         | $(call check_coverage,335)
	@$(VERIFAST) $(VERIFAST_ARGS) -disable_overflow_check queue/xQueueGenericSendFromISR.c  | $(call check_coverage,317)
	@$(VERIFAST) $(VERIFAST_ARGS)                         queue/xQueueIsQueueEmptyFromISR.c | $(call check_coverage,287)
	@$(VERIFAST) $(VERIFAST_ARGS)                         queue/xQueueIsQueueFullFromISR.c  | $(call check_coverage,287)
	@$(VERIFAST) $(VERIFAST_ARGS)                         queue/xQueuePeek.c                | $(call check_coverage,335)
	@$(VERIFAST) $(VERIFAST_ARGS)                         queue/xQueuePeekFromISR.c         | $(call check_coverage,300)
	@$(VERIFAST) $(VERIFAST_ARGS)                         queue/xQueueReceive.c             | $(call check_coverage,337)
	@$(VERIFAST) $(VERIFAST_ARGS) -disable_overflow_check queue/xQueueReceiveFromISR.c      | $(call check_coverage,314)

.PHONY: list
list:
	@$(VERIFAST) $(VERIFAST_ARGS)                         list/listLIST_IS_EMPTY.c   | $(call check_coverage,314)
	@$(VERIFAST) $(VERIFAST_ARGS)                         list/uxListRemove.c        | $(call check_coverage,440)
	@$(VERIFAST) $(VERIFAST_ARGS)                         list/vListInitialise.c     | $(call check_coverage,329)
	@$(VERIFAST) $(VERIFAST_ARGS)                         list/vListInitialiseItem.c | $(call check_coverage,316)
	@$(VERIFAST) $(VERIFAST_ARGS) -disable_overflow_check list/vListInsertEnd.c      | $(call check_coverage,410)
	@$(VERIFAST) $(VERIFAST_ARGS) -disable_overflow_check list/vListInsert.c         | $(call check_coverage,456)

.PHONY: proof_changes
proof_changes:
	@git grep "if[n]*def VERIFAST" | cut  -f 3- -d ' ' | sort | uniq
