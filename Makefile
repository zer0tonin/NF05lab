.PHONY: clean All

All:
	@echo "----------Building project:[ NF05Lab - Debug ]----------"
	@$(MAKE) -f  "NF05Lab.mk"
clean:
	@echo "----------Cleaning project:[ NF05Lab - Debug ]----------"
	@$(MAKE) -f  "NF05Lab.mk" clean
